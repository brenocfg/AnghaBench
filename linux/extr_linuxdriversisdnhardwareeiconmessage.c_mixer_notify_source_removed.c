#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t word ;
typedef  int dword ;
typedef  int byte ;
struct TYPE_5__ {size_t li_plci_b_write_pos; size_t li_plci_b_read_pos; int Id; int* li_plci_b_queue; TYPE_1__* adapter; } ;
struct TYPE_4__ {int /*<<< orphan*/  Id; } ;
typedef  TYPE_2__ PLCI ;

/* Variables and functions */
 scalar_t__ FILE_ ; 
 int LI_PLCI_B_DISC_FLAG ; 
 int LI_PLCI_B_QUEUE_ENTRIES ; 
 int UnMapController (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int,char*,int) ; 

__attribute__((used)) static byte mixer_notify_source_removed(PLCI *plci, dword plci_b_id)
{
	word plci_b_write_pos;

	plci_b_write_pos = plci->li_plci_b_write_pos;
	if (((plci->li_plci_b_read_pos > plci_b_write_pos) ? plci->li_plci_b_read_pos :
	     LI_PLCI_B_QUEUE_ENTRIES + plci->li_plci_b_read_pos) - plci_b_write_pos - 1 < 1)
	{
		dbug(1, dprintf("[%06lx] %s,%d: LI request overrun",
				(dword)((plci->Id << 8) | UnMapController(plci->adapter->Id)),
				(char *)(FILE_), __LINE__));
		return (false);
	}
	plci->li_plci_b_queue[plci_b_write_pos] = plci_b_id | LI_PLCI_B_DISC_FLAG;
	plci_b_write_pos = (plci_b_write_pos == LI_PLCI_B_QUEUE_ENTRIES - 1) ? 0 : plci_b_write_pos + 1;
	plci->li_plci_b_write_pos = plci_b_write_pos;
	return (true);
}