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

/* Variables and functions */
 int EOPNOTSUPP ; 
 int MLX5_ATOMIC_MODE_8B ; 
 int __fls (int) ; 

__attribute__((used)) static int atomic_size_to_mode(int size_mask)
{
	/* driver does not support atomic_size > 256B
	 * and does not know how to translate bigger sizes
	 */
	int supported_size_mask = size_mask & 0x1ff;
	int log_max_size;

	if (!supported_size_mask)
		return -EOPNOTSUPP;

	log_max_size = __fls(supported_size_mask);

	if (log_max_size > 3)
		return log_max_size;

	return MLX5_ATOMIC_MODE_8B;
}