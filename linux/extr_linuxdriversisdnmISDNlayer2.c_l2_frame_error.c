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
struct layer2 {int dummy; } ;
struct FsmInst {struct layer2* userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDL_ERROR_IND ; 
 int /*<<< orphan*/  l2mgr (struct layer2*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void
l2_frame_error(struct FsmInst *fi, int event, void *arg)
{
	struct layer2 *l2 = fi->userdata;

	l2mgr(l2, MDL_ERROR_IND, arg);
}