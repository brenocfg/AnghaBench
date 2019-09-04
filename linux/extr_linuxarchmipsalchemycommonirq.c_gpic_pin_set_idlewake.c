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

/* Variables and functions */
 int /*<<< orphan*/  GPIC_CFG_IDLEWAKE ; 
 int /*<<< orphan*/  au1300_gpic_chgcfg (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void gpic_pin_set_idlewake(unsigned int gpio, int allow)
{
	au1300_gpic_chgcfg(gpio, GPIC_CFG_IDLEWAKE,
			   allow ? GPIC_CFG_IDLEWAKE : 0);
}