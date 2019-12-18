#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  v4l2_std_id ;
struct xc4000_priv {int ignore_i2c_write_errors; TYPE_1__* firm; } ;
struct dvb_frontend {struct xc4000_priv* tuner_priv; } ;
struct TYPE_2__ {unsigned char* ptr; } ;

/* Variables and functions */
 int seek_firmware (struct dvb_frontend*,unsigned int,int /*<<< orphan*/ *) ; 
 int xc_load_i2c_sequence (struct dvb_frontend*,unsigned char*) ; 

__attribute__((used)) static int load_firmware(struct dvb_frontend *fe, unsigned int type,
			 v4l2_std_id *id)
{
	struct xc4000_priv *priv = fe->tuner_priv;
	int                pos, rc;
	unsigned char      *p;

	pos = seek_firmware(fe, type, id);
	if (pos < 0)
		return pos;

	p = priv->firm[pos].ptr;

	/* Don't complain when the request fails because of i2c stretching */
	priv->ignore_i2c_write_errors = 1;

	rc = xc_load_i2c_sequence(fe, p);

	priv->ignore_i2c_write_errors = 0;

	return rc;
}