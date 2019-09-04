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
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 int nx842_crypto_init (struct crypto_tfm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nx842_powernv_driver ; 

__attribute__((used)) static int nx842_powernv_crypto_init(struct crypto_tfm *tfm)
{
	return nx842_crypto_init(tfm, &nx842_powernv_driver);
}