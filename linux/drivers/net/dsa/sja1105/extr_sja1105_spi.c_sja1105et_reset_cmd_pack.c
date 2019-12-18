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
struct sja1105_reset_cmd {int /*<<< orphan*/  warm_rst; int /*<<< orphan*/  cold_rst; } ;

/* Variables and functions */
 int SJA1105_SIZE_RESET_CMD ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  sja1105_pack (void*,int /*<<< orphan*/ *,int,int,int const) ; 

__attribute__((used)) static void
sja1105et_reset_cmd_pack(void *buf, const struct sja1105_reset_cmd *reset)
{
	const int size = SJA1105_SIZE_RESET_CMD;

	memset(buf, 0, size);

	sja1105_pack(buf, &reset->cold_rst, 3, 3, size);
	sja1105_pack(buf, &reset->warm_rst, 2, 2, size);
}