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
struct nouveau_svm_fault {int inst; int addr; int access; } ;
typedef  int s64 ;

/* Variables and functions */

__attribute__((used)) static int
nouveau_svm_fault_cmp(const void *a, const void *b)
{
	const struct nouveau_svm_fault *fa = *(struct nouveau_svm_fault **)a;
	const struct nouveau_svm_fault *fb = *(struct nouveau_svm_fault **)b;
	int ret;
	if ((ret = (s64)fa->inst - fb->inst))
		return ret;
	if ((ret = (s64)fa->addr - fb->addr))
		return ret;
	/*XXX: atomic? */
	return (fa->access == 0 || fa->access == 3) -
	       (fb->access == 0 || fb->access == 3);
}