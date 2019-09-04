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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ signature; scalar_t__ cksum; } ;
struct core99_header {scalar_t__ adler; int /*<<< orphan*/  generation; TYPE_1__ hdr; } ;

/* Variables and functions */
 scalar_t__ CORE99_SIGNATURE ; 
 int /*<<< orphan*/  DBG (char*) ; 
 scalar_t__ chrp_checksum (TYPE_1__*) ; 
 scalar_t__ core99_calc_adler (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 core99_check(u8* datas)
{
	struct core99_header* hdr99 = (struct core99_header*)datas;

	if (hdr99->hdr.signature != CORE99_SIGNATURE) {
		DBG("Invalid signature\n");
		return 0;
	}
	if (hdr99->hdr.cksum != chrp_checksum(&hdr99->hdr)) {
		DBG("Invalid checksum\n");
		return 0;
	}
	if (hdr99->adler != core99_calc_adler(datas)) {
		DBG("Invalid adler\n");
		return 0;
	}
	return hdr99->generation;
}