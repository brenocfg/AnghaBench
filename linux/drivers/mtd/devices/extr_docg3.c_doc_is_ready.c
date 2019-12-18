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
struct docg3 {int dummy; } ;

/* Variables and functions */
 int DOC_CTRL_FLASHREADY ; 
 int /*<<< orphan*/  DOC_FLASHCONTROL ; 
 int doc_register_readb (struct docg3*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int doc_is_ready(struct docg3 *docg3)
{
	int ctrl;

	ctrl = doc_register_readb(docg3, DOC_FLASHCONTROL);
	return ctrl & DOC_CTRL_FLASHREADY;
}