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
typedef  int u16 ;
typedef  int /*<<< orphan*/  kuid_t ;

/* Variables and functions */
 int BIT (scalar_t__) ; 
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int HFI1_ADMIN_JKEY_RANGE ; 
 int HFI1_JKEY_MASK ; 
 scalar_t__ HFI1_JKEY_WIDTH ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_user_ns () ; 
 int from_kuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u16 generate_jkey(kuid_t uid)
{
	u16 jkey = from_kuid(current_user_ns(), uid) & HFI1_JKEY_MASK;

	if (capable(CAP_SYS_ADMIN))
		jkey &= HFI1_ADMIN_JKEY_RANGE - 1;
	else if (jkey < 64)
		jkey |= BIT(HFI1_JKEY_WIDTH - 1);

	return jkey;
}