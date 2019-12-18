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
struct parport {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECR_MODE_MASK ; 
 int /*<<< orphan*/  frob_econtrol (struct parport*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void frob_set_mode(struct parport *p, int mode)
{
	frob_econtrol(p, ECR_MODE_MASK, mode << 5);
}