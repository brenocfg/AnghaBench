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
struct snd_ivtv_card {struct snd_card* sc; int /*<<< orphan*/  v4l2_dev; } ;
struct snd_card {int /*<<< orphan*/  longname; int /*<<< orphan*/  shortname; int /*<<< orphan*/  driver; } ;
struct ivtv {int instance; char* card_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,...) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 struct ivtv* to_ivtv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_ivtv_card_set_names(struct snd_ivtv_card *itvsc)
{
	struct ivtv *itv = to_ivtv(itvsc->v4l2_dev);
	struct snd_card *sc = itvsc->sc;

	/* sc->driver is used by alsa-lib's configurator: simple, unique */
	strscpy(sc->driver, "CX2341[56]", sizeof(sc->driver));

	/* sc->shortname is a symlink in /proc/asound: IVTV-M -> cardN */
	snprintf(sc->shortname,  sizeof(sc->shortname), "IVTV-%d",
		 itv->instance);

	/* sc->longname is read from /proc/asound/cards */
	snprintf(sc->longname, sizeof(sc->longname),
		 "CX2341[56] #%d %s TV/FM Radio/Line-In Capture",
		 itv->instance, itv->card_name);

	return 0;
}