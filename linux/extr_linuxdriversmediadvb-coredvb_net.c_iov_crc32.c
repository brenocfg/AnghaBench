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
struct kvec {int /*<<< orphan*/  iov_len; int /*<<< orphan*/  iov_base; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  crc32_be (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline __u32 iov_crc32( __u32 c, struct kvec *iov, unsigned int cnt )
{
	unsigned int j;
	for (j = 0; j < cnt; j++)
		c = crc32_be( c, iov[j].iov_base, iov[j].iov_len );
	return c;
}