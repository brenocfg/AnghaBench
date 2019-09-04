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
struct fw_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_SCHEDULE_TIMEOUT ; 
 int __fw_state_wait_common (struct fw_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int fw_state_wait(struct fw_priv *fw_priv)
{
	return __fw_state_wait_common(fw_priv, MAX_SCHEDULE_TIMEOUT);
}