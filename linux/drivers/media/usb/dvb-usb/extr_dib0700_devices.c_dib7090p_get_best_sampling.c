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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_2__ {int bandwidth_hz; int frequency; } ;
struct dvb_frontend {TYPE_1__ dtv_property_cache; } ;
struct dibx090p_best_adc {int pll_loopdiv; int pll_prediv; unsigned long timf; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  deb_info (char*,int,int,...) ; 

__attribute__((used)) static int dib7090p_get_best_sampling(struct dvb_frontend *fe , struct dibx090p_best_adc *adc)
{
	u8 spur = 0, prediv = 0, loopdiv = 0, min_prediv = 1, max_prediv = 1;

	u16 xtal = 12000;
	u32 fcp_min = 1900;  /* PLL Minimum Frequency comparator KHz */
	u32 fcp_max = 20000; /* PLL Maximum Frequency comparator KHz */
	u32 fdem_max = 76000;
	u32 fdem_min = 69500;
	u32 fcp = 0, fs = 0, fdem = 0;
	u32 harmonic_id = 0;

	adc->pll_loopdiv = loopdiv;
	adc->pll_prediv = prediv;
	adc->timf = 0;

	deb_info("bandwidth = %d fdem_min =%d", fe->dtv_property_cache.bandwidth_hz, fdem_min);

	/* Find Min and Max prediv */
	while ((xtal/max_prediv) >= fcp_min)
		max_prediv++;

	max_prediv--;
	min_prediv = max_prediv;
	while ((xtal/min_prediv) <= fcp_max) {
		min_prediv--;
		if (min_prediv == 1)
			break;
	}
	deb_info("MIN prediv = %d : MAX prediv = %d", min_prediv, max_prediv);

	min_prediv = 2;

	for (prediv = min_prediv ; prediv < max_prediv; prediv++) {
		fcp = xtal / prediv;
		if (fcp > fcp_min && fcp < fcp_max) {
			for (loopdiv = 1 ; loopdiv < 64 ; loopdiv++) {
				fdem = ((xtal/prediv) * loopdiv);
				fs   = fdem / 4;
				/* test min/max system restrictions */

				if ((fdem >= fdem_min) && (fdem <= fdem_max) && (fs >= fe->dtv_property_cache.bandwidth_hz/1000)) {
					spur = 0;
					/* test fs harmonics positions */
					for (harmonic_id = (fe->dtv_property_cache.frequency / (1000*fs)) ;  harmonic_id <= ((fe->dtv_property_cache.frequency / (1000*fs))+1) ; harmonic_id++) {
						if (((fs*harmonic_id) >= ((fe->dtv_property_cache.frequency/1000) - (fe->dtv_property_cache.bandwidth_hz/2000))) &&  ((fs*harmonic_id) <= ((fe->dtv_property_cache.frequency/1000) + (fe->dtv_property_cache.bandwidth_hz/2000)))) {
							spur = 1;
							break;
						}
					}

					if (!spur) {
						adc->pll_loopdiv = loopdiv;
						adc->pll_prediv = prediv;
						adc->timf = 2396745143UL/fdem*(1 << 9);
						adc->timf += ((2396745143UL%fdem) << 9)/fdem;
						deb_info("loopdiv=%i prediv=%i timf=%i", loopdiv, prediv, adc->timf);
						break;
					}
				}
			}
		}
		if (!spur)
			break;
	}


	if (adc->pll_loopdiv == 0 && adc->pll_prediv == 0)
		return -EINVAL;
	else
		return 0;
}