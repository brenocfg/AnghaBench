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
struct tea5767_priv {int dummy; } ;
struct dvb_frontend {struct tea5767_priv* tuner_priv; } ;

/* Variables and functions */
 char const TEA5767_STEREO_MASK ; 
 int V4L2_TUNER_SUB_STEREO ; 
 int /*<<< orphan*/  tuner_dbg (char*,int) ; 

__attribute__((used)) static inline int tea5767_stereo(struct dvb_frontend *fe, const char *buffer)
{
	struct tea5767_priv *priv = fe->tuner_priv;

	int stereo = buffer[2] & TEA5767_STEREO_MASK;

	tuner_dbg("Radio ST GET = %02x\n", stereo);

	return (stereo ? V4L2_TUNER_SUB_STEREO : 0);
}