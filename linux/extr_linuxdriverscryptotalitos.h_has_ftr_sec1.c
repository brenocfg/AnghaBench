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
struct talitos_private {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline bool has_ftr_sec1(struct talitos_private *priv)
{
#if defined(CONFIG_CRYPTO_DEV_TALITOS1) && defined(CONFIG_CRYPTO_DEV_TALITOS2)
	return priv->features & TALITOS_FTR_SEC1 ? true : false;
#elif defined(CONFIG_CRYPTO_DEV_TALITOS1)
	return true;
#else
	return false;
#endif
}