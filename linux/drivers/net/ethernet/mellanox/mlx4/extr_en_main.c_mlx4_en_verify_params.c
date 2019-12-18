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
 scalar_t__ MAX_INLINE ; 
 scalar_t__ MAX_PFC_RX ; 
 scalar_t__ MAX_PFC_TX ; 
 scalar_t__ MIN_PKT_LEN ; 
 scalar_t__ inline_thold ; 
 scalar_t__ pfcrx ; 
 scalar_t__ pfctx ; 
 int /*<<< orphan*/  pr_warn (char*,scalar_t__,scalar_t__,...) ; 

__attribute__((used)) static void mlx4_en_verify_params(void)
{
	if (pfctx > MAX_PFC_TX) {
		pr_warn("mlx4_en: WARNING: illegal module parameter pfctx 0x%x - should be in range 0-0x%x, will be changed to default (0)\n",
			pfctx, MAX_PFC_TX);
		pfctx = 0;
	}

	if (pfcrx > MAX_PFC_RX) {
		pr_warn("mlx4_en: WARNING: illegal module parameter pfcrx 0x%x - should be in range 0-0x%x, will be changed to default (0)\n",
			pfcrx, MAX_PFC_RX);
		pfcrx = 0;
	}

	if (inline_thold < MIN_PKT_LEN || inline_thold > MAX_INLINE) {
		pr_warn("mlx4_en: WARNING: illegal module parameter inline_thold %d - should be in range %d-%d, will be changed to default (%d)\n",
			inline_thold, MIN_PKT_LEN, MAX_INLINE, MAX_INLINE);
		inline_thold = MAX_INLINE;
	}
}