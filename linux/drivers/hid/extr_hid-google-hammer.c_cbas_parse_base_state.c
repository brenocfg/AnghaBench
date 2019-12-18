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
typedef  int u32 ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_MKBP_BASE_ATTACHED ; 
 int get_unaligned_le32 (void const*) ; 

__attribute__((used)) static bool cbas_parse_base_state(const void *data)
{
	u32 switches = get_unaligned_le32(data);

	return !!(switches & BIT(EC_MKBP_BASE_ATTACHED));
}