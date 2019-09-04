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
typedef  int /*<<< orphan*/  u32 ;
struct cmng_init_input {int /*<<< orphan*/  port_rate; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct cmng_init {TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_TO_BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_init_fw_wrr (struct cmng_init_input const*,int /*<<< orphan*/ ,struct cmng_init*) ; 
 int /*<<< orphan*/  bnx2x_init_max (struct cmng_init_input const*,int /*<<< orphan*/ ,struct cmng_init*) ; 
 int /*<<< orphan*/  bnx2x_init_min (struct cmng_init_input const*,int /*<<< orphan*/ ,struct cmng_init*) ; 
 int /*<<< orphan*/  bnx2x_init_safc (struct cmng_init_input const*,struct cmng_init*) ; 
 int /*<<< orphan*/  memset (struct cmng_init*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void bnx2x_init_cmng(const struct cmng_init_input *input_data,
				   struct cmng_init *ram_data)
{
	u32 r_param;
	memset(ram_data, 0, sizeof(struct cmng_init));

	ram_data->port.flags = input_data->flags;

	/* number of bytes transmitted in a rate of 10Gbps
	 * in one usec = 1.25KB.
	 */
	r_param = BITS_TO_BYTES(input_data->port_rate);
	bnx2x_init_max(input_data, r_param, ram_data);
	bnx2x_init_min(input_data, r_param, ram_data);
	bnx2x_init_fw_wrr(input_data, r_param, ram_data);
	bnx2x_init_safc(input_data, ram_data);
}