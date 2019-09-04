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
struct pxa_i2c {int dummy; } ;

/* Variables and functions */
 int ICR_SCLE ; 
 int /*<<< orphan*/  _ICR (struct pxa_i2c*) ; 
 int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int i2c_pxa_is_slavemode(struct pxa_i2c *i2c)
{
	return !(readl(_ICR(i2c)) & ICR_SCLE);
}