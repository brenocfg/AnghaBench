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
struct c67x00_td {int pid_ep; int /*<<< orphan*/  td_addr; struct c67x00_td* data; } ;
struct c67x00_hcd {TYPE_1__* sie; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CY_TD_SIZE ; 
 int TD_PIDEPMASK_PID ; 
 int TD_PID_IN ; 
 int /*<<< orphan*/  c67x00_ll_write_mem_le16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct c67x00_td*,int) ; 
 int td_length (struct c67x00_td*) ; 
 int /*<<< orphan*/  td_ly_base_addr (struct c67x00_td*) ; 

__attribute__((used)) static void c67x00_send_td(struct c67x00_hcd *c67x00, struct c67x00_td *td)
{
	int len = td_length(td);

	if (len && ((td->pid_ep & TD_PIDEPMASK_PID) != TD_PID_IN))
		c67x00_ll_write_mem_le16(c67x00->sie->dev, td_ly_base_addr(td),
					 td->data, len);

	c67x00_ll_write_mem_le16(c67x00->sie->dev,
				 td->td_addr, td, CY_TD_SIZE);
}