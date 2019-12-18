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
struct mt7530_priv {int dummy; } ;
struct mt7530_dummy_poll {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_MT7530_DUMMY_POLL (struct mt7530_dummy_poll*,struct mt7530_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mt7530_read (struct mt7530_dummy_poll*) ; 

__attribute__((used)) static u32
mt7530_read(struct mt7530_priv *priv, u32 reg)
{
	struct mt7530_dummy_poll p;

	INIT_MT7530_DUMMY_POLL(&p, priv, reg);
	return _mt7530_read(&p);
}