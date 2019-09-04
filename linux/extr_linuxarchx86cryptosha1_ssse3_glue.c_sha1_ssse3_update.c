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
typedef  int /*<<< orphan*/  u8 ;
struct shash_desc {int dummy; } ;
typedef  int /*<<< orphan*/  sha1_transform_fn ;

/* Variables and functions */
 scalar_t__ sha1_transform_ssse3 ; 
 int sha1_update (struct shash_desc*,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sha1_ssse3_update(struct shash_desc *desc, const u8 *data,
			     unsigned int len)
{
	return sha1_update(desc, data, len,
			(sha1_transform_fn *) sha1_transform_ssse3);
}