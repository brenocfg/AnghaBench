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
struct cmd_desc {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int
typhoon_num_free(int lastWrite, int lastRead, int ringSize)
{
	/* this works for all descriptors but rx_desc, as they are a
	 * different size than the cmd_desc -- everyone else is the same
	 */
	lastWrite /= sizeof(struct cmd_desc);
	lastRead /= sizeof(struct cmd_desc);
	return (ringSize + lastRead - lastWrite - 1) % ringSize;
}