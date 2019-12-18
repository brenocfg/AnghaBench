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
struct regmap {int dummy; } ;
struct ade_hw_ctx {struct regmap* noc_regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADE0_QOSGENERATOR_EXTCONTROL ; 
 int /*<<< orphan*/  ADE0_QOSGENERATOR_MODE ; 
 int /*<<< orphan*/  ADE1_QOSGENERATOR_EXTCONTROL ; 
 int /*<<< orphan*/  ADE1_QOSGENERATOR_MODE ; 
 int /*<<< orphan*/  BYPASS_MODE ; 
 int /*<<< orphan*/  QOSGENERATOR_MODE_MASK ; 
 int /*<<< orphan*/  SOCKET_QOS_EN ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ade_set_medianoc_qos(struct ade_hw_ctx *ctx)
{
	struct regmap *map = ctx->noc_regmap;

	regmap_update_bits(map, ADE0_QOSGENERATOR_MODE,
			   QOSGENERATOR_MODE_MASK, BYPASS_MODE);
	regmap_update_bits(map, ADE0_QOSGENERATOR_EXTCONTROL,
			   SOCKET_QOS_EN, SOCKET_QOS_EN);

	regmap_update_bits(map, ADE1_QOSGENERATOR_MODE,
			   QOSGENERATOR_MODE_MASK, BYPASS_MODE);
	regmap_update_bits(map, ADE1_QOSGENERATOR_EXTCONTROL,
			   SOCKET_QOS_EN, SOCKET_QOS_EN);
}