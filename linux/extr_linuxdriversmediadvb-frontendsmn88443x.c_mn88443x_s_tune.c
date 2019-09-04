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
struct mn88443x_priv {struct regmap* regmap_s; } ;
struct dtv_frontend_properties {int stream_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATSIDL_S ; 
 int /*<<< orphan*/  ATSIDU_S ; 
 int /*<<< orphan*/  TSSET_S ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mn88443x_s_tune(struct mn88443x_priv *chip,
			    struct dtv_frontend_properties *c)
{
	struct regmap *r_s = chip->regmap_s;

	regmap_write(r_s, ATSIDU_S, c->stream_id >> 8);
	regmap_write(r_s, ATSIDL_S, c->stream_id);
	regmap_write(r_s, TSSET_S, 0);
}