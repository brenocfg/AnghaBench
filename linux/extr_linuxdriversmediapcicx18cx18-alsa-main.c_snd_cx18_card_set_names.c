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
struct snd_cx18_card {struct snd_card* sc; int /*<<< orphan*/  v4l2_dev; } ;
struct snd_card {int /*<<< orphan*/  longname; int /*<<< orphan*/  shortname; int /*<<< orphan*/  driver; } ;
struct cx18 {int instance; char* card_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,...) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 struct cx18* to_cx18 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_cx18_card_set_names(struct snd_cx18_card *cxsc)
{
	struct cx18 *cx = to_cx18(cxsc->v4l2_dev);
	struct snd_card *sc = cxsc->sc;

	/* sc->driver is used by alsa-lib's configurator: simple, unique */
	strlcpy(sc->driver, "CX23418", sizeof(sc->driver));

	/* sc->shortname is a symlink in /proc/asound: CX18-M -> cardN */
	snprintf(sc->shortname,  sizeof(sc->shortname), "CX18-%d",
		 cx->instance);

	/* sc->longname is read from /proc/asound/cards */
	snprintf(sc->longname, sizeof(sc->longname),
		 "CX23418 #%d %s TV/FM Radio/Line-In Capture",
		 cx->instance, cx->card_name);

	return 0;
}