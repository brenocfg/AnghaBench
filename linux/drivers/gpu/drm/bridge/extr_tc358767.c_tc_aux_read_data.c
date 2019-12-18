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
struct tc_data {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int ALIGN (size_t,int) ; 
 int /*<<< orphan*/  DP0_AUXRDATA (int /*<<< orphan*/ ) ; 
 int DP_AUX_MAX_PAYLOAD_BYTES ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,size_t) ; 
 int regmap_raw_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int tc_aux_read_data(struct tc_data *tc, void *data, size_t size)
{
	u32 auxrdata[DP_AUX_MAX_PAYLOAD_BYTES / sizeof(u32)];
	int ret, count = ALIGN(size, sizeof(u32));

	ret = regmap_raw_read(tc->regmap, DP0_AUXRDATA(0), auxrdata, count);
	if (ret)
		return ret;

	memcpy(data, auxrdata, size);

	return size;
}