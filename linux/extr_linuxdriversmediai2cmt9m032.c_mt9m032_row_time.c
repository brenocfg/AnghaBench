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
struct mt9m032 {int /*<<< orphan*/  pix_clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  div_u64 (unsigned long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_dev (struct mt9m032*) ; 

__attribute__((used)) static u32 mt9m032_row_time(struct mt9m032 *sensor, unsigned int width)
{
	unsigned int effective_width;
	u32 ns;

	effective_width = width + 716; /* empirical value */
	ns = div_u64(1000000000ULL * effective_width, sensor->pix_clock);
	dev_dbg(to_dev(sensor),	"MT9M032 line time: %u ns\n", ns);
	return ns;
}