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
struct fintek_dev {int /*<<< orphan*/  cr_ip; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_REG_DISABLE ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void fintek_config_mode_disable(struct fintek_dev *fintek)
{
	outb(CONFIG_REG_DISABLE, fintek->cr_ip);
}