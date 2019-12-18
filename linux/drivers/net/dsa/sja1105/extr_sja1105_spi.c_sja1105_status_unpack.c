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
struct sja1105_status {int /*<<< orphan*/  crcchkg; int /*<<< orphan*/  ids; int /*<<< orphan*/  crcchkl; int /*<<< orphan*/  configs; } ;

/* Variables and functions */
 int /*<<< orphan*/  sja1105_unpack (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int) ; 

__attribute__((used)) static void sja1105_status_unpack(void *buf, struct sja1105_status *status)
{
	/* So that addition translates to 4 bytes */
	u32 *p = buf;

	/* device_id is missing from the buffer, but we don't
	 * want to diverge from the manual definition of the
	 * register addresses, so we'll back off one step with
	 * the register pointer, and never access p[0].
	 */
	p--;
	sja1105_unpack(p + 0x1, &status->configs,   31, 31, 4);
	sja1105_unpack(p + 0x1, &status->crcchkl,   30, 30, 4);
	sja1105_unpack(p + 0x1, &status->ids,       29, 29, 4);
	sja1105_unpack(p + 0x1, &status->crcchkg,   28, 28, 4);
}