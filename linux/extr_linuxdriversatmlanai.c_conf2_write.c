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
struct lanai_dev {int /*<<< orphan*/  conf2; } ;

/* Variables and functions */
 int /*<<< orphan*/  Config2_Reg ; 
 int /*<<< orphan*/  reg_write (struct lanai_dev const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void conf2_write(const struct lanai_dev *lanai)
{
	reg_write(lanai, lanai->conf2, Config2_Reg);
}