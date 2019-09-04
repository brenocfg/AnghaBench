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
struct atmel_smc_cs_conf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct atmel_smc_cs_conf*,int /*<<< orphan*/ ,int) ; 

void atmel_smc_cs_conf_init(struct atmel_smc_cs_conf *conf)
{
	memset(conf, 0, sizeof(*conf));
}