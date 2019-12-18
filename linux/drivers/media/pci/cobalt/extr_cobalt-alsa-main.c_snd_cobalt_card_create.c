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
struct snd_cobalt_card {struct snd_card* sc; struct cobalt_stream* s; } ;
struct snd_card {int /*<<< orphan*/  private_free; struct snd_cobalt_card* private_data; } ;
struct cobalt_stream {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct snd_cobalt_card* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_cobalt_card_private_free ; 

__attribute__((used)) static int snd_cobalt_card_create(struct cobalt_stream *s,
				       struct snd_card *sc,
				       struct snd_cobalt_card **cobsc)
{
	*cobsc = kzalloc(sizeof(struct snd_cobalt_card), GFP_KERNEL);
	if (*cobsc == NULL)
		return -ENOMEM;

	(*cobsc)->s = s;
	(*cobsc)->sc = sc;

	sc->private_data = *cobsc;
	sc->private_free = snd_cobalt_card_private_free;

	return 0;
}