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
struct ap_perms {int /*<<< orphan*/  aqm; } ;

/* Variables and functions */
 scalar_t__ test_bit_inv (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool zcrypt_check_queue(struct ap_perms *perms, int queue)
{
	return test_bit_inv(queue, perms->aqm) ? true : false;
}