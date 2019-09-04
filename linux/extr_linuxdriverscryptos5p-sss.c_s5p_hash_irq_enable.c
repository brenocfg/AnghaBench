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
struct s5p_aes_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FCINTENSET ; 
 int /*<<< orphan*/  SSS_WRITE (struct s5p_aes_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void s5p_hash_irq_enable(struct s5p_aes_dev *dev, int flags)
{
	SSS_WRITE(dev, FCINTENSET, flags);
}