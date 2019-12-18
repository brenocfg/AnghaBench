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
struct adreno_gpu {int revn; } ;

/* Variables and functions */

__attribute__((used)) static inline bool adreno_is_a306(struct adreno_gpu *gpu)
{
	/* yes, 307, because a305c is 306 */
	return gpu->revn == 307;
}