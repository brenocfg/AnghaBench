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
struct mvneta_bm_pool {int dummy; } ;
struct mvneta_bm {int dummy; } ;
typedef  enum mvneta_bm_type { ____Placeholder_mvneta_bm_type } mvneta_bm_type ;

/* Variables and functions */

struct mvneta_bm_pool *mvneta_bm_pool_use(struct mvneta_bm *priv, u8 pool_id,
					  enum mvneta_bm_type type, u8 port_id,
					  int pkt_size) { return NULL; }