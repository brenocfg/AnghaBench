#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tda1997x_state {TYPE_2__* supplies; TYPE_1__* client; } ;
struct TYPE_4__ {int /*<<< orphan*/  supply; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int TDA1997X_NUM_SUPPLIES ; 
 int devm_regulator_bulk_get (int /*<<< orphan*/ *,int,TYPE_2__*) ; 
 int /*<<< orphan*/ * tda1997x_supply_name ; 

__attribute__((used)) static int tda1997x_get_regulators(struct tda1997x_state *state)
{
	int i;

	for (i = 0; i < TDA1997X_NUM_SUPPLIES; i++)
		state->supplies[i].supply = tda1997x_supply_name[i];

	return devm_regulator_bulk_get(&state->client->dev,
				       TDA1997X_NUM_SUPPLIES,
				       state->supplies);
}