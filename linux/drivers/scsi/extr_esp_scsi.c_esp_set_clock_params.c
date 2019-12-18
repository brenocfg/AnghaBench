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
typedef  int u8 ;
struct esp {int cfreq; int cfact; int /*<<< orphan*/  sync_defp; int /*<<< orphan*/  neg_defp; int /*<<< orphan*/  ccycle; int /*<<< orphan*/  ctick; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_HZ_TO_CYCLE (int) ; 
 int /*<<< orphan*/  ESP_NEG_DEFP (int,int) ; 
 int /*<<< orphan*/  ESP_TICK (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYNC_DEFP_SLOW ; 

__attribute__((used)) static void esp_set_clock_params(struct esp *esp)
{
	int fhz;
	u8 ccf;

	/* This is getting messy but it has to be done correctly or else
	 * you get weird behavior all over the place.  We are trying to
	 * basically figure out three pieces of information.
	 *
	 * a) Clock Conversion Factor
	 *
	 *    This is a representation of the input crystal clock frequency
	 *    going into the ESP on this machine.  Any operation whose timing
	 *    is longer than 400ns depends on this value being correct.  For
	 *    example, you'll get blips for arbitration/selection during high
	 *    load or with multiple targets if this is not set correctly.
	 *
	 * b) Selection Time-Out
	 *
	 *    The ESP isn't very bright and will arbitrate for the bus and try
	 *    to select a target forever if you let it.  This value tells the
	 *    ESP when it has taken too long to negotiate and that it should
	 *    interrupt the CPU so we can see what happened.  The value is
	 *    computed as follows (from NCR/Symbios chip docs).
	 *
	 *          (Time Out Period) *  (Input Clock)
	 *    STO = ----------------------------------
	 *          (8192) * (Clock Conversion Factor)
	 *
	 *    We use a time out period of 250ms (ESP_BUS_TIMEOUT).
	 *
	 * c) Imperical constants for synchronous offset and transfer period
         *    register values
	 *
	 *    This entails the smallest and largest sync period we could ever
	 *    handle on this ESP.
	 */
	fhz = esp->cfreq;

	ccf = ((fhz / 1000000) + 4) / 5;
	if (ccf == 1)
		ccf = 2;

	/* If we can't find anything reasonable, just assume 20MHZ.
	 * This is the clock frequency of the older sun4c's where I've
	 * been unable to find the clock-frequency PROM property.  All
	 * other machines provide useful values it seems.
	 */
	if (fhz <= 5000000 || ccf < 1 || ccf > 8) {
		fhz = 20000000;
		ccf = 4;
	}

	esp->cfact = (ccf == 8 ? 0 : ccf);
	esp->cfreq = fhz;
	esp->ccycle = ESP_HZ_TO_CYCLE(fhz);
	esp->ctick = ESP_TICK(ccf, esp->ccycle);
	esp->neg_defp = ESP_NEG_DEFP(fhz, ccf);
	esp->sync_defp = SYNC_DEFP_SLOW;
}