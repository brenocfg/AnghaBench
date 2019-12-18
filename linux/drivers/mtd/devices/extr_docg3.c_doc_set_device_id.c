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
typedef  int u8 ;
struct docg3 {int dummy; } ;

/* Variables and functions */
 int DOC_CTRL_CE ; 
 int DOC_CTRL_VIOLATION ; 
 int /*<<< orphan*/  DOC_DEVICESELECT ; 
 int /*<<< orphan*/  DOC_FLASHCONTROL ; 
 int /*<<< orphan*/  doc_dbg (char*,int) ; 
 int doc_register_readb (struct docg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  doc_writeb (struct docg3*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void doc_set_device_id(struct docg3 *docg3, int id)
{
	u8 ctrl;

	doc_dbg("doc_set_device_id(%d)\n", id);
	doc_writeb(docg3, id, DOC_DEVICESELECT);
	ctrl = doc_register_readb(docg3, DOC_FLASHCONTROL);

	ctrl &= ~DOC_CTRL_VIOLATION;
	ctrl |= DOC_CTRL_CE;
	doc_writeb(docg3, ctrl, DOC_FLASHCONTROL);
}