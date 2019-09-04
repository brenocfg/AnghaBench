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
struct tpm_space {void* context_buf; int /*<<< orphan*/ * session_buf; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int tpm2_init_space(struct tpm_space *space)
{
	space->context_buf = kzalloc(PAGE_SIZE, GFP_KERNEL);
	if (!space->context_buf)
		return -ENOMEM;

	space->session_buf = kzalloc(PAGE_SIZE, GFP_KERNEL);
	if (space->session_buf == NULL) {
		kfree(space->context_buf);
		return -ENOMEM;
	}

	return 0;
}