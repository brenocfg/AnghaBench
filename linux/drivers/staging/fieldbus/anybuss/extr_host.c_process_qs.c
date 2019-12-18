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
struct kfifo {int dummy; } ;
struct anybuss_host {struct kfifo* qs; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct kfifo*) ; 
 int /*<<< orphan*/  process_q (struct anybuss_host*,struct kfifo*) ; 

__attribute__((used)) static void process_qs(struct anybuss_host *cd)
{
	size_t i;
	struct kfifo *qs = cd->qs;
	size_t nqs = ARRAY_SIZE(cd->qs);

	for (i = 0; i < nqs; i++, qs++)
		process_q(cd, qs);
}