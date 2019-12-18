#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int BaseAddress; } ;
typedef  TYPE_1__ nsp_hw_data ;

/* Variables and functions */
 int /*<<< orphan*/  IRQCONTROL ; 
 int /*<<< orphan*/  IRQCONTROL_ALLCLEAR ; 
 int /*<<< orphan*/  IRQCONTROL_ALLMASK ; 
 int /*<<< orphan*/  IRQPHASESENCE ; 
 int /*<<< orphan*/  SCSIBUSCTRL ; 
 int /*<<< orphan*/  SCSI_RST ; 
 int SUCCESS ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  nsp_index_read (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsp_index_write (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsp_write (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsphw_init_sync (TYPE_1__*) ; 

__attribute__((used)) static int nsp_bus_reset(nsp_hw_data *data)
{
	unsigned int base = data->BaseAddress;
	int	     i;

	nsp_write(base, IRQCONTROL, IRQCONTROL_ALLMASK);

	nsp_index_write(base, SCSIBUSCTRL, SCSI_RST);
	mdelay(100); /* 100ms */
	nsp_index_write(base, SCSIBUSCTRL, 0);
	for(i = 0; i < 5; i++) {
		nsp_index_read(base, IRQPHASESENCE); /* dummy read */
	}

	nsphw_init_sync(data);

	nsp_write(base, IRQCONTROL, IRQCONTROL_ALLCLEAR);

	return SUCCESS;
}