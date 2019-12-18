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
struct xc2028_data {int /*<<< orphan*/  state; int /*<<< orphan*/  fname; } ;
struct firmware {int dummy; } ;
struct dvb_frontend {struct xc2028_data* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  XC2028_ACTIVE ; 
 int /*<<< orphan*/  XC2028_NODEV ; 
 int load_all_firmwares (struct dvb_frontend*,struct firmware const*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int /*<<< orphan*/  tuner_dbg (char*,char*) ; 
 int /*<<< orphan*/  tuner_err (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void load_firmware_cb(const struct firmware *fw,
			     void *context)
{
	struct dvb_frontend *fe = context;
	struct xc2028_data *priv = fe->tuner_priv;
	int rc;

	tuner_dbg("request_firmware_nowait(): %s\n", fw ? "OK" : "error");
	if (!fw) {
		tuner_err("Could not load firmware %s.\n", priv->fname);
		priv->state = XC2028_NODEV;
		return;
	}

	rc = load_all_firmwares(fe, fw);

	release_firmware(fw);

	if (rc < 0)
		return;
	priv->state = XC2028_ACTIVE;
}