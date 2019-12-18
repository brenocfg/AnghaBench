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
typedef  int u64 ;
struct tg3 {int dummy; } ;
struct ptp_system_timestamp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TG3_EAV_REF_CLCK_LSB ; 
 int /*<<< orphan*/  TG3_EAV_REF_CLCK_MSB ; 
 int /*<<< orphan*/  ptp_read_system_postts (struct ptp_system_timestamp*) ; 
 int /*<<< orphan*/  ptp_read_system_prets (struct ptp_system_timestamp*) ; 
 int tr32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 tg3_refclk_read(struct tg3 *tp, struct ptp_system_timestamp *sts)
{
	u64 stamp;

	ptp_read_system_prets(sts);
	stamp = tr32(TG3_EAV_REF_CLCK_LSB);
	ptp_read_system_postts(sts);
	stamp |= (u64)tr32(TG3_EAV_REF_CLCK_MSB) << 32;

	return stamp;
}