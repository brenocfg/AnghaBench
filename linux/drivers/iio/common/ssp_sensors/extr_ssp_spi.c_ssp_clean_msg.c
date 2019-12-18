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
struct ssp_msg {struct ssp_msg* buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ssp_msg*) ; 

__attribute__((used)) static void ssp_clean_msg(struct ssp_msg *m)
{
	kfree(m->buffer);
	kfree(m);
}