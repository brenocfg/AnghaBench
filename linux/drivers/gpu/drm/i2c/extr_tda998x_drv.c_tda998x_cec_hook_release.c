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
struct tda998x_priv {int dummy; } ;

/* Variables and functions */
 int CEC_ENAMODS_EN_CEC ; 
 int CEC_ENAMODS_EN_CEC_CLK ; 
 int /*<<< orphan*/  cec_enamods (struct tda998x_priv*,int,int) ; 

__attribute__((used)) static void tda998x_cec_hook_release(void *data)
{
	struct tda998x_priv *priv = data;

	cec_enamods(priv, CEC_ENAMODS_EN_CEC_CLK | CEC_ENAMODS_EN_CEC, false);
}