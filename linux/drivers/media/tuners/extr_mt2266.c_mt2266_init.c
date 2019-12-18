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
struct mt2266_priv {int dummy; } ;
struct dvb_frontend {struct mt2266_priv* tuner_priv; } ;

/* Variables and functions */
 int mt2266_writereg (struct mt2266_priv*,int,int) ; 

__attribute__((used)) static int mt2266_init(struct dvb_frontend *fe)
{
	int ret;
	struct mt2266_priv *priv = fe->tuner_priv;
	ret = mt2266_writereg(priv, 0x17, 0x6d);
	if (ret < 0)
		return ret;
	ret = mt2266_writereg(priv, 0x1c, 0xff);
	if (ret < 0)
		return ret;
	return 0;
}