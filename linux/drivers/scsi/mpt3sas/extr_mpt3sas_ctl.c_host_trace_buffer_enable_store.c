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
typedef  int /*<<< orphan*/  u8 ;
struct mpt3_diag_register {size_t buffer_type; int requested_buffer_size; int unique_id; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {int dummy; } ;
struct MPT3SAS_ADAPTER {int* diag_buffer_status; scalar_t__* diag_buffer; scalar_t__ is_driver_loading; scalar_t__ pci_error_recovery; scalar_t__ remove_host; scalar_t__ shost_recovery; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  EINVAL ; 
 size_t MPI2_DIAG_BUF_TYPE_TRACE ; 
 int MPT3_DIAG_BUFFER_IS_REGISTERED ; 
 int MPT3_DIAG_BUFFER_IS_RELEASED ; 
 int /*<<< orphan*/  _ctl_diag_register_2 (struct MPT3SAS_ADAPTER*,struct mpt3_diag_register*) ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 int /*<<< orphan*/  ioc_info (struct MPT3SAS_ADAPTER*,char*) ; 
 int /*<<< orphan*/  memset (struct mpt3_diag_register*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpt3sas_send_diag_release (struct MPT3SAS_ADAPTER*,size_t,int /*<<< orphan*/ *) ; 
 struct MPT3SAS_ADAPTER* shost_priv (struct Scsi_Host*) ; 
 int sscanf (char const*,char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static ssize_t
host_trace_buffer_enable_store(struct device *cdev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	struct Scsi_Host *shost = class_to_shost(cdev);
	struct MPT3SAS_ADAPTER *ioc = shost_priv(shost);
	char str[10] = "";
	struct mpt3_diag_register diag_register;
	u8 issue_reset = 0;

	/* don't allow post/release occurr while recovery is active */
	if (ioc->shost_recovery || ioc->remove_host ||
	    ioc->pci_error_recovery || ioc->is_driver_loading)
		return -EBUSY;

	if (sscanf(buf, "%9s", str) != 1)
		return -EINVAL;

	if (!strcmp(str, "post")) {
		/* exit out if host buffers are already posted */
		if ((ioc->diag_buffer[MPI2_DIAG_BUF_TYPE_TRACE]) &&
		    (ioc->diag_buffer_status[MPI2_DIAG_BUF_TYPE_TRACE] &
		    MPT3_DIAG_BUFFER_IS_REGISTERED) &&
		    ((ioc->diag_buffer_status[MPI2_DIAG_BUF_TYPE_TRACE] &
		    MPT3_DIAG_BUFFER_IS_RELEASED) == 0))
			goto out;
		memset(&diag_register, 0, sizeof(struct mpt3_diag_register));
		ioc_info(ioc, "posting host trace buffers\n");
		diag_register.buffer_type = MPI2_DIAG_BUF_TYPE_TRACE;
		diag_register.requested_buffer_size = (1024 * 1024);
		diag_register.unique_id = 0x7075900;
		ioc->diag_buffer_status[MPI2_DIAG_BUF_TYPE_TRACE] = 0;
		_ctl_diag_register_2(ioc,  &diag_register);
	} else if (!strcmp(str, "release")) {
		/* exit out if host buffers are already released */
		if (!ioc->diag_buffer[MPI2_DIAG_BUF_TYPE_TRACE])
			goto out;
		if ((ioc->diag_buffer_status[MPI2_DIAG_BUF_TYPE_TRACE] &
		    MPT3_DIAG_BUFFER_IS_REGISTERED) == 0)
			goto out;
		if ((ioc->diag_buffer_status[MPI2_DIAG_BUF_TYPE_TRACE] &
		    MPT3_DIAG_BUFFER_IS_RELEASED))
			goto out;
		ioc_info(ioc, "releasing host trace buffer\n");
		mpt3sas_send_diag_release(ioc, MPI2_DIAG_BUF_TYPE_TRACE,
		    &issue_reset);
	}

 out:
	return strlen(buf);
}