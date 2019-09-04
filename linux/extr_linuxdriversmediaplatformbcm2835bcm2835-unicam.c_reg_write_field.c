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
typedef  int /*<<< orphan*/  u32 ;
struct unicam_cfg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  reg_read (struct unicam_cfg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (struct unicam_cfg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_field (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void reg_write_field(struct unicam_cfg *dev, u32 offset,
				   u32 field, u32 mask)
{
	u32 val = reg_read((dev), (offset));

	set_field(&val, field, mask);
	reg_write((dev), (offset), val);
}