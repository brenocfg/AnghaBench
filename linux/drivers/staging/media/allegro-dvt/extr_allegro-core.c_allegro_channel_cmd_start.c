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
struct allegro_channel {int dummy; } ;

/* Variables and functions */
#define  ALLEGRO_STATE_DRAIN 130 
 int /*<<< orphan*/  ALLEGRO_STATE_ENCODING ; 
#define  ALLEGRO_STATE_STOPPED 129 
#define  ALLEGRO_STATE_WAIT_FOR_BUFFER 128 
 int EBUSY ; 
 int allegro_get_state (struct allegro_channel*) ; 
 int /*<<< orphan*/  allegro_set_state (struct allegro_channel*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int allegro_channel_cmd_start(struct allegro_channel *channel)
{
	switch (allegro_get_state(channel)) {
	case ALLEGRO_STATE_DRAIN:
	case ALLEGRO_STATE_WAIT_FOR_BUFFER:
		return -EBUSY;
	case ALLEGRO_STATE_STOPPED:
		allegro_set_state(channel, ALLEGRO_STATE_ENCODING);
		break;
	default:
		return 0;
	}

	return 0;
}