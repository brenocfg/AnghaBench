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
struct ef4_nic {int dummy; } ;

/* Variables and functions */
 int falcon_read_nvram (struct ef4_nic*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int falcon_test_nvram(struct ef4_nic *efx)
{
	return falcon_read_nvram(efx, NULL);
}