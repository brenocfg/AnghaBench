#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {scalar_t__* cmnd; TYPE_1__* device; } ;
struct scatterlist {int offset; } ;
struct TYPE_2__ {scalar_t__ channel; scalar_t__ id; scalar_t__ lun; } ;

/* Variables and functions */
 scalar_t__ IPS_ADAPTER_ID ; 
 scalar_t__ IPS_IOCTL_COMMAND ; 
 int /*<<< orphan*/  METHOD_TRACE (char*,int) ; 
 char* kmap_atomic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (char*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 struct scatterlist* scsi_sglist (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 

__attribute__((used)) static int ips_is_passthru(struct scsi_cmnd *SC)
{
	unsigned long flags;

	METHOD_TRACE("ips_is_passthru", 1);

	if (!SC)
		return (0);

	if ((SC->cmnd[0] == IPS_IOCTL_COMMAND) &&
	    (SC->device->channel == 0) &&
	    (SC->device->id == IPS_ADAPTER_ID) &&
	    (SC->device->lun == 0) && scsi_sglist(SC)) {
                struct scatterlist *sg = scsi_sglist(SC);
                char  *buffer;

                /* kmap_atomic() ensures addressability of the user buffer.*/
                /* local_irq_save() protects the KM_IRQ0 address slot.     */
                local_irq_save(flags);
                buffer = kmap_atomic(sg_page(sg)) + sg->offset;
                if (buffer && buffer[0] == 'C' && buffer[1] == 'O' &&
                    buffer[2] == 'P' && buffer[3] == 'P') {
                        kunmap_atomic(buffer - sg->offset);
                        local_irq_restore(flags);
                        return 1;
                }
                kunmap_atomic(buffer - sg->offset);
                local_irq_restore(flags);
	}
	return 0;
}