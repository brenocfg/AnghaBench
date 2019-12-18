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
typedef  int /*<<< orphan*/  u32 ;
struct mvneta_bm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVNETA_BM_CONFIG_REG ; 
 int /*<<< orphan*/  mvneta_bm_read (struct mvneta_bm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvneta_bm_write (struct mvneta_bm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mvneta_bm_config_clear(struct mvneta_bm *priv, u32 mask)
{
	u32 val;

	val = mvneta_bm_read(priv, MVNETA_BM_CONFIG_REG);
	val &= ~mask;
	mvneta_bm_write(priv, MVNETA_BM_CONFIG_REG, val);
}