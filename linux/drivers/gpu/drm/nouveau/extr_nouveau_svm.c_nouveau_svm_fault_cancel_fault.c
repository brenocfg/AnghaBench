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
struct nouveau_svm_fault {int /*<<< orphan*/  client; int /*<<< orphan*/  gpc; int /*<<< orphan*/  hub; int /*<<< orphan*/  inst; } ;
struct nouveau_svm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_svm_fault_cancel (struct nouveau_svm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nouveau_svm_fault_cancel_fault(struct nouveau_svm *svm,
			       struct nouveau_svm_fault *fault)
{
	nouveau_svm_fault_cancel(svm, fault->inst,
				      fault->hub,
				      fault->gpc,
				      fault->client);
}