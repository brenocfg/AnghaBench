#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int cfg; } ;
struct atmel_pmecc_user {TYPE_1__ cache; } ;

/* Variables and functions */
 int PMECC_CFG_SECTOR1024 ; 

__attribute__((used)) static int get_sectorsize(struct atmel_pmecc_user *user)
{
	return user->cache.cfg & PMECC_CFG_SECTOR1024 ? 1024 : 512;
}