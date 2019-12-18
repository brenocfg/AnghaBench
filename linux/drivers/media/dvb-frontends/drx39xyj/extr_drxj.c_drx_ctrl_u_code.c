#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct i2c_device_addr {int dummy; } ;
struct firmware {int size; int /*<<< orphan*/  const* data; } ;
struct drxu_code_info {char* mc_file; } ;
struct drxu_code_block_hdr {int addr; int size; int flags; scalar_t__ CRC; } ;
struct drx_demod_instance {struct firmware const* firmware; TYPE_2__* i2c; struct i2c_device_addr* my_i2c_dev_addr; } ;
typedef  enum drxu_code_action { ____Placeholder_drxu_code_action } drxu_code_action ;
typedef  int dr_xaddr_t ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int DRX_UCODE_CRC_FLAG ; 
 scalar_t__ DRX_UCODE_MAGIC_WORD ; 
 int DRX_UCODE_MAX_BUF_SIZE ; 
 int EINVAL ; 
 int EIO ; 
#define  UCODE_UPLOAD 129 
#define  UCODE_VERIFY 128 
 void* be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int drx_check_firmware (struct drx_demod_instance*,int /*<<< orphan*/  const*,unsigned int) ; 
 scalar_t__ drx_u_code_compute_crc (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  drxdap_fasi_read_block (struct i2c_device_addr*,int,scalar_t__,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  drxdap_fasi_write_block (struct i2c_device_addr*,int,scalar_t__,int /*<<< orphan*/  const*,int) ; 
 int memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,int,int,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int drx_ctrl_u_code(struct drx_demod_instance *demod,
		       struct drxu_code_info *mc_info,
		       enum drxu_code_action action)
{
	struct i2c_device_addr *dev_addr = demod->my_i2c_dev_addr;
	int rc;
	u16 i = 0;
	u16 mc_nr_of_blks = 0;
	u16 mc_magic_word = 0;
	const u8 *mc_data_init = NULL;
	u8 *mc_data = NULL;
	unsigned size;
	char *mc_file;

	/* Check arguments */
	if (!mc_info || !mc_info->mc_file)
		return -EINVAL;

	mc_file = mc_info->mc_file;

	if (!demod->firmware) {
		const struct firmware *fw = NULL;

		rc = request_firmware(&fw, mc_file, demod->i2c->dev.parent);
		if (rc < 0) {
			pr_err("Couldn't read firmware %s\n", mc_file);
			return rc;
		}
		demod->firmware = fw;

		if (demod->firmware->size < 2 * sizeof(u16)) {
			rc = -EINVAL;
			pr_err("Firmware is too short!\n");
			goto release;
		}

		pr_info("Firmware %s, size %zu\n",
			mc_file, demod->firmware->size);
	}

	mc_data_init = demod->firmware->data;
	size = demod->firmware->size;

	mc_data = (void *)mc_data_init;
	/* Check data */
	mc_magic_word = be16_to_cpu(*(__be16 *)(mc_data));
	mc_data += sizeof(u16);
	mc_nr_of_blks = be16_to_cpu(*(__be16 *)(mc_data));
	mc_data += sizeof(u16);

	if ((mc_magic_word != DRX_UCODE_MAGIC_WORD) || (mc_nr_of_blks == 0)) {
		rc = -EINVAL;
		pr_err("Firmware magic word doesn't match\n");
		goto release;
	}

	if (action == UCODE_UPLOAD) {
		rc = drx_check_firmware(demod, (u8 *)mc_data_init, size);
		if (rc)
			goto release;
		pr_info("Uploading firmware %s\n", mc_file);
	} else {
		pr_info("Verifying if firmware upload was ok.\n");
	}

	/* Process microcode blocks */
	for (i = 0; i < mc_nr_of_blks; i++) {
		struct drxu_code_block_hdr block_hdr;
		u16 mc_block_nr_bytes = 0;

		/* Process block header */
		block_hdr.addr = be32_to_cpu(*(__be32 *)(mc_data));
		mc_data += sizeof(u32);
		block_hdr.size = be16_to_cpu(*(__be16 *)(mc_data));
		mc_data += sizeof(u16);
		block_hdr.flags = be16_to_cpu(*(__be16 *)(mc_data));
		mc_data += sizeof(u16);
		block_hdr.CRC = be16_to_cpu(*(__be16 *)(mc_data));
		mc_data += sizeof(u16);

		pr_debug("%zd: addr %u, size %u, flags 0x%04x, CRC 0x%04x\n",
			(mc_data - mc_data_init), block_hdr.addr,
			 block_hdr.size, block_hdr.flags, block_hdr.CRC);

		/* Check block header on:
		   - data larger than 64Kb
		   - if CRC enabled check CRC
		 */
		if ((block_hdr.size > 0x7FFF) ||
		    (((block_hdr.flags & DRX_UCODE_CRC_FLAG) != 0) &&
		     (block_hdr.CRC != drx_u_code_compute_crc(mc_data, block_hdr.size)))
		    ) {
			/* Wrong data ! */
			rc = -EINVAL;
			pr_err("firmware CRC is wrong\n");
			goto release;
		}

		if (!block_hdr.size)
			continue;

		mc_block_nr_bytes = block_hdr.size * ((u16) sizeof(u16));

		/* Perform the desired action */
		switch (action) {
		case UCODE_UPLOAD:	/* Upload microcode */
			if (drxdap_fasi_write_block(dev_addr,
							block_hdr.addr,
							mc_block_nr_bytes,
							mc_data, 0x0000)) {
				rc = -EIO;
				pr_err("error writing firmware at pos %zd\n",
				       mc_data - mc_data_init);
				goto release;
			}
			break;
		case UCODE_VERIFY: {	/* Verify uploaded microcode */
			int result = 0;
			u8 mc_data_buffer[DRX_UCODE_MAX_BUF_SIZE];
			u32 bytes_to_comp = 0;
			u32 bytes_left = mc_block_nr_bytes;
			u32 curr_addr = block_hdr.addr;
			u8 *curr_ptr = mc_data;

			while (bytes_left != 0) {
				if (bytes_left > DRX_UCODE_MAX_BUF_SIZE)
					bytes_to_comp = DRX_UCODE_MAX_BUF_SIZE;
				else
					bytes_to_comp = bytes_left;

				if (drxdap_fasi_read_block(dev_addr,
						    curr_addr,
						    (u16)bytes_to_comp,
						    (u8 *)mc_data_buffer,
						    0x0000)) {
					pr_err("error reading firmware at pos %zd\n",
					       mc_data - mc_data_init);
					return -EIO;
				}

				result = memcmp(curr_ptr, mc_data_buffer,
						bytes_to_comp);

				if (result) {
					pr_err("error verifying firmware at pos %zd\n",
					       mc_data - mc_data_init);
					return -EIO;
				}

				curr_addr += ((dr_xaddr_t)(bytes_to_comp / 2));
				curr_ptr =&(curr_ptr[bytes_to_comp]);
				bytes_left -=((u32) bytes_to_comp);
			}
			break;
		}
		default:
			return -EINVAL;
			break;

		}
		mc_data += mc_block_nr_bytes;
	}

	return 0;

release:
	release_firmware(demod->firmware);
	demod->firmware = NULL;

	return rc;
}