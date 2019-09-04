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
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 unsigned int le16_to_cpu (int /*<<< orphan*/  const) ; 

__attribute__((used)) static unsigned int regmap_parse_16_le(const void *buf)
{
	const __le16 *b = buf;

	return le16_to_cpu(b[0]);
}