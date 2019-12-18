#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct fsg_lun {scalar_t__ sense_data; scalar_t__ unit_attention_data; scalar_t__ info_valid; scalar_t__ sense_data_info; } ;
struct fsg_common {int* cmnd; scalar_t__ data_dir; int data_size; int data_size_from_cmnd; int cmnd_size; int phase_error; int residue; int usb_amount_left; unsigned int lun; scalar_t__ bad_lun_okay; struct fsg_lun* curlun; } ;
typedef  enum data_direction { ____Placeholder_data_direction } data_direction ;

/* Variables and functions */
 int DATA_DIR_NONE ; 
 scalar_t__ DATA_DIR_UNKNOWN ; 
 int /*<<< orphan*/  DBG (struct fsg_common*,char*,...) ; 
 int EINVAL ; 
 int INQUIRY ; 
 int REQUEST_SENSE ; 
 scalar_t__ SS_INVALID_FIELD_IN_CDB ; 
 scalar_t__ SS_MEDIUM_NOT_PRESENT ; 
 scalar_t__ SS_NO_SENSE ; 
 int /*<<< orphan*/  VDBG (struct fsg_common*,char*,char const*,int,char const,int,int,char*) ; 
 int /*<<< orphan*/  fsg_lun_is_open (struct fsg_lun*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const,int) ; 

__attribute__((used)) static int check_command(struct fsg_common *common, int cmnd_size,
			 enum data_direction data_dir, unsigned int mask,
			 int needs_medium, const char *name)
{
	int			i;
	unsigned int		lun = common->cmnd[1] >> 5;
	static const char	dirletter[4] = {'u', 'o', 'i', 'n'};
	char			hdlen[20];
	struct fsg_lun		*curlun;

	hdlen[0] = 0;
	if (common->data_dir != DATA_DIR_UNKNOWN)
		sprintf(hdlen, ", H%c=%u", dirletter[(int) common->data_dir],
			common->data_size);
	VDBG(common, "SCSI command: %s;  Dc=%d, D%c=%u;  Hc=%d%s\n",
	     name, cmnd_size, dirletter[(int) data_dir],
	     common->data_size_from_cmnd, common->cmnd_size, hdlen);

	/*
	 * We can't reply at all until we know the correct data direction
	 * and size.
	 */
	if (common->data_size_from_cmnd == 0)
		data_dir = DATA_DIR_NONE;
	if (common->data_size < common->data_size_from_cmnd) {
		/*
		 * Host data size < Device data size is a phase error.
		 * Carry out the command, but only transfer as much as
		 * we are allowed.
		 */
		common->data_size_from_cmnd = common->data_size;
		common->phase_error = 1;
	}
	common->residue = common->data_size;
	common->usb_amount_left = common->data_size;

	/* Conflicting data directions is a phase error */
	if (common->data_dir != data_dir && common->data_size_from_cmnd > 0) {
		common->phase_error = 1;
		return -EINVAL;
	}

	/* Verify the length of the command itself */
	if (cmnd_size != common->cmnd_size) {

		/*
		 * Special case workaround: There are plenty of buggy SCSI
		 * implementations. Many have issues with cbw->Length
		 * field passing a wrong command size. For those cases we
		 * always try to work around the problem by using the length
		 * sent by the host side provided it is at least as large
		 * as the correct command length.
		 * Examples of such cases would be MS-Windows, which issues
		 * REQUEST SENSE with cbw->Length == 12 where it should
		 * be 6, and xbox360 issuing INQUIRY, TEST UNIT READY and
		 * REQUEST SENSE with cbw->Length == 10 where it should
		 * be 6 as well.
		 */
		if (cmnd_size <= common->cmnd_size) {
			DBG(common, "%s is buggy! Expected length %d "
			    "but we got %d\n", name,
			    cmnd_size, common->cmnd_size);
			cmnd_size = common->cmnd_size;
		} else {
			common->phase_error = 1;
			return -EINVAL;
		}
	}

	/* Check that the LUN values are consistent */
	if (common->lun != lun)
		DBG(common, "using LUN %u from CBW, not LUN %u from CDB\n",
		    common->lun, lun);

	/* Check the LUN */
	curlun = common->curlun;
	if (curlun) {
		if (common->cmnd[0] != REQUEST_SENSE) {
			curlun->sense_data = SS_NO_SENSE;
			curlun->sense_data_info = 0;
			curlun->info_valid = 0;
		}
	} else {
		common->bad_lun_okay = 0;

		/*
		 * INQUIRY and REQUEST SENSE commands are explicitly allowed
		 * to use unsupported LUNs; all others may not.
		 */
		if (common->cmnd[0] != INQUIRY &&
		    common->cmnd[0] != REQUEST_SENSE) {
			DBG(common, "unsupported LUN %u\n", common->lun);
			return -EINVAL;
		}
	}

	/*
	 * If a unit attention condition exists, only INQUIRY and
	 * REQUEST SENSE commands are allowed; anything else must fail.
	 */
	if (curlun && curlun->unit_attention_data != SS_NO_SENSE &&
	    common->cmnd[0] != INQUIRY &&
	    common->cmnd[0] != REQUEST_SENSE) {
		curlun->sense_data = curlun->unit_attention_data;
		curlun->unit_attention_data = SS_NO_SENSE;
		return -EINVAL;
	}

	/* Check that only command bytes listed in the mask are non-zero */
	common->cmnd[1] &= 0x1f;			/* Mask away the LUN */
	for (i = 1; i < cmnd_size; ++i) {
		if (common->cmnd[i] && !(mask & (1 << i))) {
			if (curlun)
				curlun->sense_data = SS_INVALID_FIELD_IN_CDB;
			return -EINVAL;
		}
	}

	/* If the medium isn't mounted and the command needs to access
	 * it, return an error. */
	if (curlun && !fsg_lun_is_open(curlun) && needs_medium) {
		curlun->sense_data = SS_MEDIUM_NOT_PRESENT;
		return -EINVAL;
	}

	return 0;
}